s/\([ _]\)a/\1A/g
s/\([ _]\)b/\1B/g
s/\([ _]\)c/\1C/g
s/\([ _]\)d/\1D/g
s/\([ _]\)e/\1E/g
s/\([ _]\)f/\1F/g
s/\([ _]\)g/\1G/g
s/\([ _]\)h/\1H/g
s/\([ _]\)i/\1I/g
s/\([ _]\)j/\1J/g
s/\([ _]\)k/\1K/g
s/\([ _]\)l/\1L/g
s/\([ _]\)m/\1M/g
s/\([ _]\)n/\1N/g
s/\([ _]\)o/\1O/g
s/\([ _]\)p/\1P/g
s/\([ _]\)q/\1Q/g
s/\([ _]\)r/\1R/g
s/\([ _]\)s/\1S/g
s/\([ _]\)t/\1T/g
s/\([ _]\)u/\1U/g
s/\([ _]\)v/\1V/g
s/\([ _]\)w/\1W/g
s/\([ _]\)x/\1X/g
s/\([ _]\)y/\1Y/g
s/\([ _]\)z/\1Z/g                
s/ # \(.*\)/                                 { Advance (1); return \1_Token; }/
s/ ## \(.*\)/                             { Advance (2); return \1_Token; }/
s/ ### \(.*\)/                         { Advance (3); return \1_Token; }/
s/ #### \(.*\)/                     { Advance (4); return \1_Token; }/
s/ ##### \(.*\)/                 { Advance (5); return \1_Token; }/
s/ ###### \(.*\)/             { Advance (6); return \1_Token; }/
s/ ####### \(.*\)/         { Advance (7); return \1_Token; }/
s/ ######## \(.*\)/     { Advance (8); return \1_Token; }/
s/ ######### \(.*\)/ { Advance (9); return \1_Token; }/
