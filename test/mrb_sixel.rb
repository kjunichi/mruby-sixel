##
## Sixel Test
##

assert("Sixel#hello") do
  t = SixelEncoder.new 
  assert_equal("dummy", t.hello)
end
