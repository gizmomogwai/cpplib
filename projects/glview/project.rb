cxx_configuration do
  exe(
    "glview",
    :sources => FileList["*.cpp"],
    :dependencies => ["net", "io", "sgtools-glut", "image"],
  )
end
