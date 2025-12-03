project('advent-of-code', 'cpp', default_options: ['default_library=static', 'warning_level=1', 'werror=false', 'cpp_std=c++17', 'optimization=3', ], version:'0.0.1')

dir_base = meson.current_source_dir()

dir_install = join_paths(dir_base, 'result')

inc_dirs = include_directories(
  'inc',
)

source = [
  'src/argumentParsing.cpp',
  'src/evaluator.cpp',
  'src/main.cpp',
  'src/d01.cpp',
  'src/d02.cpp',
  'src/d03.cpp',
  'src/d04.cpp',
]

adventUtility = subproject('adventUtility')
adventUtility_dep = adventUtility.get_variable('adventUtility_dep')

argp_dep = dependency('argparse')

executable(
  'advent',
  source,
  include_directories:inc_dirs,
  dependencies:[
    argp_dep,
    adventUtility_dep,
  ],
  install:true,
  install_dir:dir_install
)

