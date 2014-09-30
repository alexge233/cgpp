FILE(REMOVE_RECURSE
  "libcgpp.0.1-static.pdb"
  "libcgpp.0.1-static.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/cgpp.0.1-static.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
