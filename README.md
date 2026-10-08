# gbgoffice3: an unofficial GTK3 port of gbgoffice

**Porting of [gbgoffice](http://gbgoffice.info/) from GTK2 (gtkmm 2.4) to GTK3 (gtkmm 3.0) was done *entirely* by Claude, by Anthropic.** Therefore, **no** credit goes to me for this AI slop. The program seems to build and run just fine on [CRUX](https://crux.nu/), however, be warned and use at your own risk.

## First level dependencies:
[gtkmm-3.0](https://download.gnome.org/sources/gtkmm/3.24/)

## Dictionaries
This ships the [bgoffice](https://bgoffice.sourceforge.net/) disctionaries bundled in, so no need to install them from [full-pack](https://sourceforge.net/projects/bgoffice/files/Full%20Pack%20of%20Dictionaries/1.0/) separately.

## Reasoning
The last version of gbgoffice is 1.4, released in 2006. Debian provided 11 patches for gbgoffice in [Trixie](https://packages.debian.org/trixie/gbgoffice) and seems they aredropping the package from _testing_ (https://tracker.debian.org/news/1702050/gbgoffice-removed-from-testing/). 

As for me, I use CRUX and I'd like to remove the [gtkmm-2](https://download.gnome.org/sources/gtkmm/2.24/) dependency. Also, GTK2 will be dropped sooner or later.
