# CMake generated Testfile for 
# Source directory: /home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/AnisotropicClassic/Testing/Cxx
# Build directory: /home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/AnisotropicClassic/Testing/Cxx
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AnisotropicClassicTest "/home/alexandrefreitas/MestradoBibliotecas/Slicer/Slicer/Slicer-SuperBuild-Debug/Slicer-build/Slicer" "--launcher-no-splash" "--launcher-additional-settings" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/AdditionalLauncherSettings.ini" "--launch" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/AnisotropicClassic/Testing/Cxx/AnisotropicClassicTest" "--compare" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/AnisotropicClassic/Data/Baseline/AnisotropicClassicTest.nhdr" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/Testing/Temporary/AnisotropicClassicTest.nhdr" "ModuleEntryPoint" "--sigma" "2.5" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/AnisotropicClassic/Data/Input/CTHeadAxial.nhdr" "/home/alexandrefreitas/Projetos/Slicer/AnisotropicClassic/build/Testing/Temporary/AnisotropicClassicTest.nhdr")
set_tests_properties(AnisotropicClassicTest PROPERTIES  LABELS "AnisotropicClassic")
