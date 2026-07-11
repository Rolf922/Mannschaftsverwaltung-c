# Mannschaftsverwaltung in C

Dieses Projekt wurde im Rahmen des Erlernens der   Programmiersprache C  entwickelt.

## Projektidee

Das Programm verwaltet Fußballmannschaften und deren Spieler. Im Laufe der Übungen wurde das Projekt schrittweise erweitert.

## Versionen

| Version | Inhalt |
|--------|--------|
| v0.1 | Grundfunktionen und Datumsfunktionen |
| v0.2 | Projektstruktur, Menü und Datenstrukturen |
| v0.3 | Mannschaften und Spieler erfassen und auflisten |
| v0.4 | Laden und Speichern der Daten in einer XML-ähnlichen Datei |
| v0.5 | Sortieren der Spieler mit eigener Quicksort-Funktion |
| v0.6 | Doppelt verkettete Liste für Mannschaften und Löschen von Mannschaften |

## Kompilieren

```bash
gcc main.c menu.c teams.c tools.c datetime.c database.c sort.c list.c -o mannschaft
