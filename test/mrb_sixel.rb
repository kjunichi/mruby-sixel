##
## Sixel Test
##

assert("Sixel#hello") do
  t = SixelEncoder.new 
  assert_equal("hello", t.hello)
end
