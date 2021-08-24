cxx_configuration do
  exe "glview",
    :sources => FileList["*.cpp"],
    :dependencies => ["net", "io", "sgtools", "image", Framework.new("GLUT"), Framework.new("OpenGL")]
end
