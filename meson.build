project('tp3', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

tree = library('tree', 'tree.c', 'tree.h')

exe = executable('tp3-decod-morse', 'main.c', c_args: ['-DDECOD_MORSE'], link_with: tree)
exe = executable('tp3-decod-ascii', 'main.c', link_with: tree)
