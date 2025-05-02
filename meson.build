project(
    'Top Down Shooter',
    'cpp',
    default_options: ['cpp_std=c++17', 'default_library=static'],
)

kraken_proj = subproject('kraken-engine')
kraken_dep = kraken_proj.get_variable('kraken_engine_dep')

inc = include_directories('include')
src = [
    'main.cpp',
    'src/player.cpp',
    'src/bullet.cpp',
    'src/enemy.cpp',
    'src/tankenemy.cpp',
    'src/fastenemy.cpp',

]

executable('app', src, include_directories: inc, dependencies: kraken_dep)