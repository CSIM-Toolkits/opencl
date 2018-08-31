# CMake generated Testfile for 
# Source directory: /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/DilateErode/Testing/Cxx
# Build directory: /home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(DilateErodeTest "/home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/Slicer-build/Slicer" "--launcher-no-splash" "--launcher-additional-settings" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/AdditionalLauncherSettings.ini" "--launch" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Testing/Cxx/DilateErodeTest" "--compare" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Data/Baseline/DilateErodeTest.nhdr" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/Testing/Temporary/DilateErodeTest.nhdr" "ModuleEntryPoint" "--sigma" "2.5" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/DilateErode/Data/Input/CTHeadAxial.nhdr" "/home/alexandrefreitas/Projetos/Slicer/DilateErodeOpencl/build/Testing/Temporary/DilateErodeTest.nhdr")
set_tests_properties(DilateErodeTest PROPERTIES  LABELS "DilateErode")
