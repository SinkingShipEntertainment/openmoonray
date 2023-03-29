name = 'openmoonray'

authors = [
    'PSW Rendering and Shading',
    'moonbase-dev@dreamworks.com'
]

# NOTE: version = <ext_version>.sse.<sse_version>
version = "1.0.0.0.sse.1.0.0"

description = 'OpenMoonRay package'

with scope("config") as c:
    # Determine location to release: internal (int) vs external (ext)

    # NOTE: Modify this variable to reflect the current package situation
    release_as = "ext"

    # The `c` variable here is actually rezconfig.py
    # `release_packages_path` is a variable defined inside rezconfig.py

    import os
    if release_as == "int":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_INT"]
    elif release_as == "ext":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_EXT"]

    #c.build_thread_count = "physical_cores"

# https://docs.openmoonray.org/getting-started/installation/moonray-dependencies/

requires = [
    # 'mkl',  # can be installed using yum, but want to build from source
    'embree-3.12.1',
    'optix_sdk-7.3.0',
    'lua',
    'libmicrohttpd-0.9.37',
    'log4cplus-1.1.2',
    'jsoncpp',
    'random123',
    'blosc-1.17.0',
    'tbb-2019.6',
    'boost-1.76.0',
    'libjpeg',
    'libtiff',
    'openexr-3.1.5',
    'oidn-1.4.3',
    'ocio-2.1.1',
    'oiio-2.3.15.0.sse.2',
    'OpenSubdiv-3.5.0',
    'openvdb-9.1.0',
    'usd-22.11',
    'qt-5.14.1',
]

private_build_requires = [
    'cppunit-1.15.0',
    'ispc-1.14.1',
    'python-3.9'
]

variants = [
    ["platform-linux", "arch-x86_64", "os-centos-7"],
]

# If want to use Ninja, run:
# rez-build -i --cmake-build-system "ninja"
# rez-release --cmake-build-system "ninja"
#
# Pass cmake arguments (with debug symbols):
# rez-build -i -- -DBoost_NO_BOOST_CMAKE=On -DBoost_NO_SYSTEM_PATHS=True
# rez-release -- -DBoost_NO_BOOST_CMAKE=On -DBoost_NO_SYSTEM_PATHS=True

def pre_build_commands():
    command("source /opt/rh/devtoolset-6/enable")

def commands():
    env.ARRAS_SESSION_PATH.prepend('{root}/sessions')
    # env.CMAKE_PREFIX_PATH.prepend('{root}')
    env.HDMOONRAY_DOUBLESIDED.prepend('1')
    env.MOONRAY_CLASS_PATH.prepend('{root}/coredata')
    env.MOONRAY_DSO_PATH.prepend('{root}/rdl2dso')
    env.RDL2_DSO_PATH.prepend('{root}/rdl2dso')

    env.PXR_PLUGIN_PATH.prepend('{root}/plugin')
    env.PXR_PLUGIN_PATH.prepend('{root}/adapters')

    env.PATH.prepend('{root}/bin')
    env.LD_LIBRARY_PATH.prepend('{root}/lib64')
    env.PYTHONPATH.prepend('{root}/python/lib/')

    env.HOUDINI_PATH.prepend('{root}/houdini')
