# Non-sync'ed prefs

The [API](https://www.maptoolkit.com/doc/static-maps/) requires a key, which you need to supply, as a constant:

```
s" My_API_KEY" const mykey
```

It is picked up and concatenated to the URL in test32.fs:

```
s" tests/test43.prefs" fload
mykey str+
```
