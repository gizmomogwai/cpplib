cxx_configuration do
  exe "gunzip-benchmark",
    :sources => FileList['src/main/cpp/**/*.cpp'],
    :includes => ['src/main/cpp'],
    :dependencies => ['net', 'io']
end
