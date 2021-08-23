cxx_configuration do
  exe "glview",
    :sources => FileList["*.cpp"],
    :dependencies => ["net", "io", "sgtools", "image", BinaryLibrary.new("glut"), BinaryLibrary.new("gl")]
end
