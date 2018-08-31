# CMake generated Testfile for 
# Source directory: /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/SobelFilterOpenCL/Testing/Cxx
# Build directory: /home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/SobelFilterOpenCL/Testing/Cxx
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SobelFilterOpenCLTest "/home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/Slicer-build/Slicer" "--launcher-no-splash" "--launcher-additional-settings" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/AdditionalLauncherSettings.ini" "--launch" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/SobelFilterOpenCL/Testing/Cxx/SobelFilterOpenCLTest" "--compare" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/SobelFilterOpenCL/Data/Baseline/SobelFilterOpenCLTest.nhdr" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/Testing/Temporary/SobelFilterOpenCLTest.nhdr" "ModuleEntryPoint" "--sigma" "2.5" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/SobelFilterOpenCL/Data/Input/CTHeadAxial.nhdr" "/home/alexandrefreitas/Projetos/Slicer/SobelFilterOpenCL/build/Testing/Temporary/SobelFilterOpenCLTest.nhdr")
set_tests_properties(SobelFilterOpenCLTest PROPERTIES  LABELS "SobelFilterOpenCL")
