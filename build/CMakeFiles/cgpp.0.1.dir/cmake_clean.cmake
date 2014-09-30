FILE(REMOVE_RECURSE
  "libcgpp.0.1.pdb"
  "libcgpp.0.1.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/cgpp.0.1.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
