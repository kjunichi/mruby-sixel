##
## sixel for mruby Test
##

assert("sixel for mruby#hello") do
  t = sixel for mruby.new "hello"
  assert_equal("hello", t.hello)
end

assert("sixel for mruby#bye") do
  t = sixel for mruby.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("sixel for mruby.hi") do
  assert_equal("hi!!", sixel for mruby.hi)
end
