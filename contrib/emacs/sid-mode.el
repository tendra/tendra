;;; sid-mode-el -- Major mode for editing sid grammar files

;; Author: Amos B. Haven <nonce@tendra.org>
;; Created: 14 Aug 2003
;; Keywords: sid, tendra, major-mode, grammar, ll(coolj) for all coolj <= 1

;; Copyright (c) 2003, The Tendra Project <http://www.tendra.org/>
;; All rights reserved.
;;
;; Redistribution and use in source and binary forms, with or without
;; modification, are permitted provided that the following conditions
;; are met:
;; 1. Redistributions of source code must retain the above copyright
;;    notice unmodified, this list of conditions, and the following
;;    disclaimer.
;; 2. Redistributions in binary form must reproduce the above copyright
;;    notice, this list of conditions and the following disclaimer in the
;;    documentation and/or other materials provided with the distribution.
;;
;; THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
;; IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
;; OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
;; IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
;; INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
;; NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
;; THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;;
;; $TenDRA$
;;

;;; Commentary:
;;
;; This mode allows users to edit sid grammar files in style
;; and comfort.  A sid user manual can be found at:
;; http://www.tendra.org/docs/

;;; Revisions
;; 
;;  14 Aug 2003
;;      -- Initial version.  Syntax highlighting for comments and
;;          sid section delimeters, basic left column indentation.
;;

;;; Code:

(defvar sid-mode-hook nil)
(defvar sid-mode-map nil
  "Keymap for sid major mode")

; if the user has not set a keymap, assign the default
(if sid-mode-map nil
  (setq sid-mode-map (make-keymap)))

; associate .sid files with sid-mode
(setq auto-mode-alist
          (append
           '(("\\.sid\\'" . sid-mode))
           auto-mode-alist))

; Define some keywords.  At present, only the section names are
;  define.  The list is optimized by regexp-opt.
(defconst sid-font-lock-keywords-1
  (list
   '("^%\\(?:\\(?:entry\\|\\(?:production\\|t\\(?:erminal\\|ype\\)\\)s\\)%\\)"
     . font-lock-keyword-face))
  "Minimal highlighting expressions for sid mode")

; Define syntax table for sid mode
(defvar sid-mode-syntax-table nil
  "Syntax table for sid-mode.")

(defun sid-create-syntax-table ()
  (if sid-mode-syntax-table
      ()
    (setq sid-mode-syntax-table (make-syntax-table))
    (modify-syntax-entry ?_ "w" sid-mode-syntax-table)
    (modify-syntax-entry ?/ ". 124b" sid-mode-syntax-table)
    (modify-syntax-entry ?* ". 23" sid-mode-syntax-table)
    (modify-syntax-entry ?\n "> b" sid-mode-syntax-table))
  (set-syntax-table sid-mode-syntax-table))


; Indentation.  At present, lines are indented to the left.
;   There's much more to do here.
(defun sid-indent-line ()
  "Indent current line as sid code."
  (interactive)
  (beginning-of-line)
  (indent-line-to 0))

(defvar sid-font-lock-keywords sid-font-lock-keywords-1
  "Default highlighting expressions for sid mode.")

(defun sid-mode ()
  "Major mode for editing sid grammar files"
  (interactive)
  (kill-all-local-variables)
  (sid-create-syntax-table)
  ;; Set up font-lock
  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults
	'(sid-font-lock-keywords))
  ;; Register our indentation function
  (make-local-variable 'indent-line-function)
  (setq indent-line-function 'sid-indent-line)
  (setq major-mode 'sid-mode)
  (setq mode-name "SID")
  (run-hooks 'sid-mode-hook))


(provide 'sid-mode)

;;; sid-mode.el ends here




