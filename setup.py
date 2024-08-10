from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import setuptools

eigen_include_dir = "/usr/include/eigen3"

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __str__(self):
        import pybind11
        return pybind11.get_include()

ext_modules = [
    Extension(
        'voxelforge_cpp',  # Ensure this matches the PYBIND11_MODULE macro
        sources=['VoxelForge/voxel.cpp', 'VoxelForge/octree.cpp', 'VoxelForge/main.cpp'],  # Include all .cpp files
        include_dirs=[
            get_pybind_include(),
            # get_pybind_include(user=True),
            eigen_include_dir,
        ],
        extra_compile_args=['-std=c++17'],  # Use C++17 standard
        libraries=['stdc++'],  # Link against the C++ standard library
        language='c++'
    ),
]


setup(
    name='VoxelForge',
    version='0.1',
    author='Andrew Garcia',
    author_email='garcia.gtr@gmail.com',
    description='A high-performance Python package written in C++ for efficient voxel and mesh model creation.',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    zip_safe=False,
    packages=['VoxelForge'],
    install_requires=[
        'pybind11>=2.6.0',
        'torch'
    ],
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C++',
        'Operating System :: OS Independent',
    ],
)
