# -*- coding: utf-8 -*-
import os, sys

unittestflags = (['@run_all', '--unittest-xml']
                 if os.environ.get('BROKEN_CUSTOM_ARGS_UNITTESTS') else [])

name = 'mcrt_denoise'

if 'early' not in locals() or not callable(early):
    def early(): return lambda x: x

@early()
def version():
    """
    Increment the build in the version.
    """
    _version = '2.4'
    from rezbuild import earlybind
    return earlybind.version(this, _version)

description = 'mcrt_denoise package'

authors = [
    'PSW Rendering and Shading',
    'moonbase-dev@dreamworks.com'
]

help = ('For assistance, '
        "please contact the folio's owner at: moonbase-dev@dreamworks.com")

if 'cmake' in sys.argv:
    build_system = 'cmake'
    build_system_pbr = 'cmake_modules'
else:
    build_system = 'scons'
    build_system_pbr = 'bart_scons-10'

variants = [
    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2020.3', 'icc-19.0.5.281.x.2'],
    ['os-CentOS-7', 'opt_level-debug', 'refplat-vfx2020.3', 'icc-19.0.5.281.x.2'],
    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2020.3', 'gcc-6.3.x.2'],
    ['os-CentOS-7', 'opt_level-debug', 'refplat-vfx2020.3', 'gcc-6.3.x.2'],

    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2021.0', 'gcc-9.3.x.1'],
    ['os-CentOS-7', 'opt_level-debug', 'refplat-vfx2021.0', 'gcc-9.3.x.1'],
    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2021.0', 'clang-13'],

    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2022.0', 'gcc-9.3.x.1'],
    ['os-CentOS-7', 'opt_level-debug', 'refplat-vfx2022.0', 'gcc-9.3.x.1'],
]

conf_rats_variants = [
    ['os-CentOS-7', 'opt_level-optdebug', 'refplat-vfx2020.3', 'icc-19.0.5.281.x.2', 'python-2.7'],
    ['os-CentOS-7', 'opt_level-debug', 'refplat-vfx2020.3', 'icc-19.0.5.281.x.2', 'python-2.7'],
]

scons_targets = ['@install'] + unittestflags
sconsTargets = {
    'refplat-vfx2020.3': scons_targets,
    'refplat-vfx2021.0': scons_targets,
    'refplat-vfx2022.0': scons_targets,
}

requires = [
  'cuda-11.3.0.x',
  'openimagedenoise',
  'optix-7.3.0.x',
  'scene_rdl2-11.4'
]

private_build_requires = [
    build_system_pbr,
    'cppunit',
]

if build_system is 'cmake':
    def commands():
        prependenv('CMAKE_MODULE_PATH', '{root}/lib64/cmake')
        prependenv('LD_LIBRARY_PATH', '{root}/lib64')
        prependenv('PATH', '{root}/bin')
else:
    def commands():
        prependenv('LD_LIBRARY_PATH', '{root}/lib')
        prependenv('PATH', '{root}/bin')

uuid = '47ff6209-1bfc-4c6f-92f0-0067563ffcb8'

config_version = 0