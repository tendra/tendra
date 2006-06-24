-- $Header:$
--

-- 
-- NOTES
--   This file is added by Umass for the purpose of adding more error recovery
--   power to Ayacc.
--

package Error_Report_File is
--
-- TITLE:	package Error_Report_File
--    Output the code which allows users to see what the error token was.
--
-- LANGUAGE:
--    Ada
--
-- PERSONNEL:
--    AUTHOR: Benjamin Hurwitz
--    DATE: Jul 27 1990
--
-- OVERVIEW:
--    Export the procedure Write_File which outputs all the code to the
--    file {base_name}_error_report.a
--
-- UPDATES:
--

	procedure Write_File;

end Error_Report_File;
