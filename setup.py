from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
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
    url='https://github.com/andrewrgarcia/VoxelForge',
    description='A high-performance Python package for efficient voxel and mesh model creation, with C++ backend.',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext},
    packages=setuptools.find_packages(),
    license='BSD-3-Clause',  # Specify your license here
    zip_safe=False,
    install_requires=[
        'pybind11>=2.6.0',
        'torch'
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: BSD License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: C++',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.7',
)
