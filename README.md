# diskscape

A colorful terminal tool that visualizes disk usage with ASCII bar charts.

## Build

```
gcc -o diskscape diskscape.c main.c - lm
```

## Usage

```
./diskscape <path>
```

## Flags
The following flags are available:
```plantuml
./diskscape <path> --top <N>
```
Using the `--top` flag will limit the top N directories to be displayed.

```plantuml
./diskscape <path> --hide-empty
```
Using the `--hide-empty` flag will hide directories which take no space.

