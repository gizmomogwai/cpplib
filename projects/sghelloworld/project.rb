cxx_configuration do
  exe(
    "sghelloworld",
    :sources => FileList["*.cpp"],
    :dependencies => ["sgtools-glut"],
  )
end
