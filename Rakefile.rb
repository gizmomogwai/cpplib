require 'cxx'

flags = {
#  :DEFINES => ['UNIT_TEST','EXAMPLE=main'],
  :FLAGS => ['-O0', '-g3', '-Wall', '-Werror']
}

cxx(Dir['**/project.rb'], 'out', "gcc", './') do |tc|
  tc[:COMPILER][:C].update(flags)
  tc[:COMPILER][:CPP].update(flags)
  tc[:LINKER].update(flags)
  # tc[:TARGET_OS] = :UNIX | OSX | :WINDOWS
end
