import os
import subprocess

def compile(module_name):
    source_file = f'{module_name}.cpp'

    CONDA_PREFIX = 'C:\\Anaconda\\envs\\django_ml_env\\'

    print("Compiling module...")
    vcvars_path = r'"C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"'

    cmd = (
        f'CALL {vcvars_path} && '
        f'cl /LD /std:c++17 /EHsc '  # <-- IMPORTANT FLAGS ADDED HERE
        f'/I"{CONDA_PREFIX}\\include" '
        f'/I"{CONDA_PREFIX}\\Lib\\site-packages\\pybind11\\include" '
        f'{source_file} '
        f'/link /LIBPATH:"{CONDA_PREFIX}\\libs" '
        f'/OUT:{module_name}.pyd'
    )

    if subprocess.call(cmd, shell=True) != 0:
        raise RuntimeError("Compilation failed")

    print(f"✅ Module '{module_name}' compiled successfully!")