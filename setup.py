from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools

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
        'VoxelForge.voxel',
        ['VoxelForge/voxel.cpp'],
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
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
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C++',
        # 'License :: OSI Approved :: MIT License', 
        'Operating System :: OS Independent',
    ],
)


