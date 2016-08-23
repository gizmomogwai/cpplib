cxx_configuration do
  exe "midi-server",
    :sources => FileList['**/*.cpp'],
    :includes => ['include'],
    :dependencies => [BinaryLibrary.new('rtmidi'), 'net']
end
