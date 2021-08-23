require 'cxx'

flags = {
#  :DEFINES => ['UNIT_TEST','EXAMPLE=main'],
  :FLAGS => [
    '-std=c++11',
    '-Ofast',
    '-g', '-Wall', "-Wno-deprecated-declarations",
    #"-DOPENEXIF_NO_IJG",
    '-fsanitize=address',
    '-fno-omit-frame-pointer',
  ]
}

cxx(Dir['**/project.rb'], 'out', "gcc", './') do |tc|
  tc[:COMPILER][:C].update(flags)
  tc[:COMPILER][:CPP].update(flags)
  tc[:LINKER].update(flags)
  # tc[:TARGET_OS] = :UNIX | OSX | :WINDOWS
end
