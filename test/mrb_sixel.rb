##
## Sixel Test
##

assert("Sixel#hello") do
  t = Sixel.new "hello"
  assert_equal("hello", t.hello)
end

assert("Sixel#bye") do
  t = Sixel.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Sixel.hi") do
  assert_equal("hi!!", Sixel.hi)
end
