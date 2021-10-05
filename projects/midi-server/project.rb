cxx_configuration do
#  exe "midi-server",
#    :sources => FileList['src/main/cpp/**/*.cpp'],
#    :includes => ['src/main/cpp'],
#    :dependencies => [BinaryLibrary.new('rtmidi'), 'net']
end
