[README.md for TrinityCore](./README_old.md)

This project is aimed to fix, optimize and develop playerbots based on TrinityCore / SingleCore.

## Bug Fix

- Party member heal target error for pet (will make healer bots stuck).

- Inifinite loop of lifeblood and bless of narru (will make bots stuck).

- Fix dispel spell on party member can be cast correctly.

## Spell Casting Optimize

- Speed up interval of two spells (without too much delay).

- Resurrect spell available, now bots will resurrect dead party member automatically.

## Class Optimize

### Druid

- Healer druid optimize. Now can use more spells like wild growth. And will cast to tree of life form.

- Caster form druid damage cycle optimize.

### Hunter

- Damage cycle optimize. (mainly for shoot talent)

- Use dragonhawk aura instead of hawk aura.

### Warlock

- Damage cycle optimize. (mainly for affliction talent)

## Combat Strategy

- fix resurrect on combat bug (reset strategy after accept resurrect).

## Misc

- Now the number of random bots will be correct according to configuration file.

- Use auctionhouse bots instead of ahbots.

- Change level of rndbot(uniform distribution), fix level bug for dk(> 55)

- Add Chinese localization for quests(sql update).

- Add class spell for rndbots base on their level. (e.g. tame pet for hunter, bear form for druid, ...)

- Add for food and drink to rndbots.

- Loot strategy modify, now bots will always give up their roll.

- Add orange / legendary to bots init. (not so efficient)

- Now you can correctly summon your guild member by `.bot add <name>`

- Bots with higher level (>=5) will not accept your group invitation. (except GM account).


