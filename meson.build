project('triangle-peg', 'c',
  default_options: [
    'c_std=c2x'
  ]
)

# if (host_machine.system() == 'windows')
#   add_project_link_arguments('-lgdi32', '-lwinmm', language: 'c')
# endif

root = meson.current_source_dir()
raylib = dependency('raylib')

sources = files(
  'src/main.c',
  'src/peg.c',
  'src/utils.c',
)

executable('exe', sources,
  include_directories: ['include'],
  install_dir: root + '/bin',
  dependencies: raylib,
  install: true)
