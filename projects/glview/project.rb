cxx_configuration do
  exe "glview",
    :sources => FileList["*.cpp"],
    :dependencies => ["net", "io", "sgtools", "image", "GLUT", "OpenGL"]
end
