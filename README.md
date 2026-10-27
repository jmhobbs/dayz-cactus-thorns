# DayZ Cactus Thorns

Running through the prickly-pear cacti added with Badlands/Nasdara (`BushHard_b_OpuntiaFicusIndica_*`) now has consequences.

## How it works

When a player moves through a cactus fast enough (jog or sprint by default), the server picks the area that was hit, legs (70%) or upper body, and rolls:

### Thorns

Adds the thorns status, shown as a badge next to the sick icon. Getting thorns always comes with a cut and a single health hit.

While thorns are in, the player:
  - slowly loses blood
  - limps slightly
  - can't sprint

Thorns remain until pulled out with pliers.

### Cut

Gets a bleeding cut on a leg or forearm. Worn clothing in that area takes damage: pants and shoes for legs, top and vest for the upper body.


After a contact there is a cooldown (5 s by default), so one pass through a cactus gives one roll.

### Cactus-proof clothing

Heavy clothing in the hit area lowers chances of both.

## Configuration

The config is created with defaults on server startup at `$profile:CactusConsequences.json`.

| Key | Default | Meaning |
|---|---|---|
| `CactusClassNames` | `["BushHard_b_OpuntiaFicusIndica"]` | Object type name prefixes treated as cacti |
| `TriggerWhileWalking` | `false` | Walking (including crouched) triggers contact |
| `TriggerWhileJogging` | `true` | Jogging (including crouch-running) triggers contact |
| `TriggerWhileSprinting` | `true` | Sprinting triggers contact |
| `ContactCooldownSeconds` | `5.0` | Seconds between contact rolls for one player |
| `LegHitChance` | `0.7` | Chance a contact hits the legs rather than the upper body |
| `CutChance` | `0.5` | Chance of a cut when no new thorns went in, before protection |
| `ClothingDamage` | `8.0` | Health removed from each worn item in the hit area on a cut |
| `ThornsChance` | `0.25` | Chance of thorns, before protection |
| `ThornsHealthDamage` | `5.0` | Health hit when thorns go in |
| `ThornsBloodLossPerMinute` | `30.0` | Blood lost per minute while thorns are in |
| `ThornsInjuryLevel` | `1` | Minimum limp while thorns are in: 0 none, 1 slight, 2 medium, 3 heavy (also blocks sprint), 4 worst |
| `ThornsBlockSprint` | `true` | Thorns prevent sprinting |
| `PliersDamage` | `2.0` | Health removed from the pliers per removal |
| `CactusProofItems` | see file | `{ "ClassName", "Protection" }` entries. `ClassName` matches subclasses, so a `_ColorBase` class covers all colors. `Protection` runs from 0 to 1, where 1 fully blocks that area |
