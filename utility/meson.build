project('adventUtility', 'cpp', default_options: ['default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17', ], version:'0.0.1')

inc_dirs = include_directories('inc/utility')

inc_dir_base = include_directories('inc')

source = [
  'src/combinatorics.cpp',
  'src/commonAlg.cpp',
  'src/fileOps.cpp',
  'src/point.cpp',
  'src/stringUtils.cpp',
]

adventUtility = library(
  'adventUtility',
  source,
  include_directories:inc_dirs,
  dependencies:[
  ],
)

adventUtility_dep = declare_dependency(
  include_directories: inc_dir_base,
  link_with: adventUtility,
)

