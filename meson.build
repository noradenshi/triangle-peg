project('triangle-peg', 'c',
  default_options: [
    'prefix=/home/noradenshi/Projects/triangle-peg',
    'c_std=c2x'
  ]
)

cc = meson.get_compiler('c')

deps = [ cc.find_library('raylib') ]

sources = files(
  'src/main.c',
  'src/peg.c',
  'src/utils.c',
)

executable('exe', sources,
  include_directories: ['include'],
  dependencies: deps)
