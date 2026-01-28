from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        "binary_forest_animal_classifier",
        ["binary_forest_swimmer_classifier.cpp"],
        include_dirs=[pybind11.get_include()],
        language="c++",
        extra_compile_args=["-O3", "-std=c++17"],
    )
]

setup(
    name="binary_forest_animal_classifier",
    version="0.0.0",
    ext_modules=ext_modules,
)