# 🔴⚫ ADS Praktikum 3 – Rot-Schwarz-Baum (Red-Black Tree)

Implementierung eines **Rot-Schwarz-Baums** mit AVL-Balancierung in C++ im Rahmen des Moduls *Algorithmen und Datenstrukturen* an der FH Aachen.

## Thema

Ein Rot-Schwarz-Baum ist ein selbstbalancierender binärer Suchbaum. Durch Rotationen und Farbregeln bleibt der Baum immer balanciert — das garantiert O(log n) für Einfügen, Suchen und Löschen.

## Funktionalitäten

- Knoten einfügen mit automatischer Balancierung
- Links- und Rechtsrotation zur Strukturkorrektur
- Überprüfung der Rot-Schwarz-Kriterien
- Level-Order Ausgabe (Baumstruktur sichtbar)
- Suchfunktion
- Unit-Tests mit Catch2

## Technologien & Konzepte

- C++17
- Rot-Schwarz-Baum Algorithmus
- Baum-Rotationen (Links/Rechts)
- Rekursive Traversierung
- Level-Order Traversierung (BFS)
- OOP mit Header/Source Trennung

##  Projektstruktur

```
ADS-Praktikum3-RedBlackTree/
├── Tree.h          → Klassen-Definition mit Rotations-Methoden
├── Tree.cpp        → Implementierung inkl. Balancierung
├── TreeNode.h      → Knoten mit Farb-Attribut (Rot/Schwarz)
├── TreeNode.cpp    → Implementierung des Knotens
├── TreeTest.cpp    → Unit-Tests (Catch2)
├── main.cpp        → Hauptprogramm
└── catch.h         → Catch2 Test-Framework
```

## ▶Kompilieren & Ausführen

```bash
g++ -std=c++17 -o rbtree main.cpp Tree.cpp TreeNode.cpp TreeTest.cpp
./rbtree
```

## Modul

**Algorithmen und Datenstrukturen (ADS)**  
Fachhochschule Aachen – Wirtschaftsinformatik

##  Autor

**Landry Channel Kamgang Fogang**
