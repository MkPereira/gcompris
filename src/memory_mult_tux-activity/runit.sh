activity=memory_mult_tux
type=memory

plugindir=.
if [ -f ../memory-activity/.libs/lib$type.so ]
then
  plugindir=../memory-activity/.libs
fi

./gcompris.bin -L $plugindir -P . -A ../memory-activity/resources \
    --config-dir=. -M activity \
    --locale_dir=./locale -l /math/algebramenu/memory_op_group_tux/$activity $*
