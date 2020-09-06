/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FIELD_ITER_INCLUDED
#define FIELD_ITER_INCLUDED


/*
		ITERATE ARRAY ELEMENTS, BASES AND MEMBERS OF OBJECTS

		This encapsulates the process of iterating the members of arrays structs and unions
		primarily to facilitate aggregate initialisation, but may be used for any purpose
		that requires aggregate objects to be explored in the same order.

		It is also intended that this code:

		- Allows agregate initialisation code to have a more singular focus.

		- Moves several operations, such as retrieving the name of a member into a place
			where one might expect their code to be disoverable.

		- Semantics are hygenic and idiomatic C.
*/

/*
		Each aggregate can be an array or a struct/union/class and has identifiable phases.

		For structs/unions/classes, IS_AggregateBase and IS_AggregateMembers identifies
		whether the current definition applies to a base or a member of the type that
		initialized this recursion level (see (field_iterator_init,field_iterator_push)
		and field_iterator_pop.
*/
typedef enum _FieldIteratorStage_t {
	IS_Unstarted,
	IS_Array,
	IS_AggregateBase,
	IS_AggregateMembers
} FieldIteratorStage_t;

typedef enum _FieldIteratorResult_t {
	IS_Success,
	IS_Ended,
	IS_ErrorIncompleteTemplateExpansion,
	IS_ErrorNonAggregate,
	IS_ErrorHasCtor
} FieldIteratorResult_t;

struct _FieldIteratorBody_t;
typedef struct _FieldIteratorBody_t FieldIteratorBody_t;

typedef struct _FieldIterator_t {
	BUFFER *bf;
	FieldIteratorBody_t *body;
	int overall_index;
} FieldIterator_t;

/*
		Remove one recursion level from the field iterator returning BOOL_FALSE if there
		are no more levels.
*/
int field_iterator_pop(FieldIterator_t *_sf_iter);

/*
		Given a TYPE and CV_SPEC, push these onto the iteration stack, allowing downstream
		code to iterate them and use _sf_iter->bf to get the correct name of the field
		being examined.	 When the iteration halts, exiting this level via field_iterator_pop
		allows the previous layer to continue.
*/
void field_iterator_push(FieldIterator_t *_sf_iter, TYPE t, CV_SPEC cv);

/*
		Begin use of a FieldIterator_t, which may be declared:

		BUFFER field_name_buffer = { 0 };
		FieldIterator_t field_iterator_for_something = { &field_name_buffer };

		Also has the effect of doing field_iterator_push(t,cv)
*/
void field_iterator_init(FieldIterator_t *_sf_iter, TYPE t, CV_SPEC cv);

/*
		Retrieve the current stage of iteration for structs, unions and classes or
		indicate that an array definition is being iterated.	If the array definition
		does not contain a definite bound, the user must abandon it at some point as
		field_iterator_next will never return false.
*/
FieldIteratorStage_t field_iterator_get_stage(FieldIterator_t *_sf_iter);

/*
		Retrieve a TYPE related to the current iteration.	 If over an array, it is the
		type of the array element, if in the base stage of struct/union/class iteration,
		it retrieves the type of the base class currently being examined, and if in the
		member phase, the type of the member being viewed.
*/
TYPE field_iterator_get_subtype(FieldIterator_t *_sf_iter);

/*
		Get the DECL_SPEC associated with the currently iterated member or base.
*/
int field_iterator_get_decl_spec(FieldIterator_t *_sf_iter);

/*
		Get the offset of the currently iterated member.
*/
OFFSET field_iterator_get_offset(FieldIterator_t *_sf_iter);

/*
		Get the index of the currently iterated item.
*/
int field_iterator_get_index(FieldIterator_t *_sf_iter);

/*
		Get the overall index of the currently iterated item as though each scalar
		element of every embedded structure is a sibling at the same level.
*/
int field_iterator_get_overall_index(FieldIterator_t *_sf_iter);

/*
		Destroy any used heap space.	Will automatically destroy recursion.
*/
void field_iterator_free(FieldIterator_t *_sf_iter);

/*
		Get the CV_SPEC of the currently focused member.	May not match those given
		in field_iterator_init/field_iterator_push if any members are mutable.
*/
CV_SPEC field_iterator_get_effective_cv_spec(FieldIterator_t *_sf_iter);

/*
		Focus the next member returning BOOL_FALSE if this recursion level can't
		yield any more results.
*/
int field_iterator_next(FieldIterator_t *_sf_iter);

#endif /* FIELD_ITER_INCLUDED */
