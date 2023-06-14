project('tp3', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

tree = library('tree', 'tree.c', 'tree.h')

exe = executable('tp3', 'main.c', link_with: tree)

run_target('run', command: exe)
