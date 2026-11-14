
# Adatstruktúra
```c
typedef struct El {
    int cel;
    double suly;
    struct El *kov;
} El;

typedef struct Csucs {
    int id;
    El *szomszedok;
    struct Csucs *kov;
} Csucs;

typedef struct Graf {
   Csucs *csucsok;
    int csucsCnt;
    int elCnt;
} Graf;
```

![[bmeProg1NZHdatastructure.drawio.svg]]

//page

# Memóriakezelési alapelvek.

- A Gráf elemei dinamikusan foglaltak
- A Gráf felszabadítására csak a freeGraf() függvényt lehet használni, a memóriaszivárgás elkerülése érdekében.
- Az algoritmusok a segédtömbjeiket maguk szabadítják fel.
- Az algoritmusok által visszaadott gráfokat a felhasználónak magának kell felszabadítania.


//page
# Modulok
- Main
- fileIo - Filok kezelésére szolgáló 
- algoritmus
- graf
- menu
## Main
A fő modul, itt ér össze az össze modul.
A fő függvénynek két bemenete van, az első a source csv file a második a kimeneti csv file. 
Pléda Bemeneti CSV FIle
```csv
1;2;1.0
2;1;1.0
1;3;2.0
3;1;2.0
2;4;4.0
4;2;4.0
```
//page
## Fileio  - Modul
A Filok kezelésére használt modul. 
általa biztosított függvények:
### Beolvasás
```c
Graf *grafBeolvas(const char *fajlnev);
```
#### Bemenet 
	egy string pointere ami a beolvasandó filenevet tartalmazza. A megadott filenak azonos mappában kell lenni a binary-val. 

#### Működés:
	A függvény beolvassa a filet.
	Ellenőrzi a file tagolását.
	Létrehozza és eltárolja a gárfot

#### Hibakezelés: 
	A Következő hibákat kezeli a függvény, amelyek esetében NULL pointerrel tér vissza:
		A fajlnev egy NULL pointer
		File Nem létezik
		File permission error (A futtató user nem olvashatja a kért filet.)
		Hibás Memória foglalás

#### Kimenet
	A Létrejött gráfra mutató pointert adja vissza a függvény

//page
## algoritmus  - Modul

### BFS
```c
Graf *bfs(const Graf *srcGraf, int startId);
```
#### Bemenet
	A üggvénynek két bemenete van. Az első a gráf dinamikusan foglalt címe. A második a kezdő node id-ja. 

#### Működés
	A függvény létrehoz egy kimeneti gráfot ami a bfs-t lefuttatótt feszítőfát fogja tartalmazni. 
	A gráfra felveszi a kezdőnodeot. 
	Létrehoz egy listát amiben a felfedezett éleket fogja tárolni. 
	Felveszi az első él szomszédait a listába és a gráfba. 
	Lép a listában a következőre, majd felveszi azok szomszédait is a listára, amennyiben azok még nincsenek benne valahol a gráfban. 
	FIFO algoritmust követi.
	Majd így megkapjuk a bfs-gráfot.
	Ha a bejárás sorrendje érdeklne, akkor a lista tartalmazná ezt.

#### Hibakezelés
	A Következő hibákat kezeli a függvény, amelyek esetében NULL pointerrel tér vissza:
		Hibás Memóriafoglalás
		Hibás bemeneti gráf (NULL)
		Hibás bemeneti kezdő id (A Gráfban nem szereplő id)

#### Kimenet
	A függvény visszatér a egy gráf dinamikusan foglalt pointer címével.


//page
### DFS

```c
Graf *dfs(const Graf *srcGraf, int startId);
```
#### Bemenet
	A függvénynek két bemenete van. Az első a gráf dinamikusan foglalt címe. A második a kezdő node id-ja. 

#### Működés
	A függvény létrehoz egy kimeneti gráfot ami a dfs-t lefuttatótt feszítőfát fogja tartalmazni. 
	Létrehoz egy látogatott listát ahol tárolja az eddig látogatott nodeok id-ját. 
	Rekurzívan végigmegy a nodeok-on, amíg nem talál olyat amiből nem indul node még nem felfedezett nodra. Közben felveszi ezekez a nodeokat a gárfra.
	A DFS prioritásul a *szomszedok láncolt listát használja. 

#### Hibakezelés
	A Következő hibákat kezeli a függvény, amelyek esetében NULL pointerrel tér vissza:
		Hibás Memóriafoglalás
		Hibás bemeneti gráf (NULL)
		Hibás bemeneti kezdő id (A Gráfban nem szereplő id)

#### Kimenet
	A függvény visszatér a egy gráf dinamikusan foglalt pointer címével.

//page
## graf  - Modul

### Gráf létrehozása

```c
Graf *createGraf(void);
```
#### Működés
Foglal memóriaterületet egy üres gráfnak majd beállítja annak alap adatait. 
#### Hibakezelés
	A Következő hibákat kezeli a függvény, amelyek esetében NULL pointerrel tér vissza:
		Hibás memóriakezelés

#### Kiemenet
	A függvény a dinamiksan foglalt gráf pointerével tér vissza


### Gráf Felszabadítása

```c
void freeGraf(Graf *graf);
```
#### Bemenet
	A függvénynek egy bemenete van, a felszabadítandó gráf címe.

#### Működés
	A függvény végigiterál az összes csúcson, csúcsonként az összes élen és felszabadítja azokat.

### Csúcskeresés

```c
Csucs *csucsFind(Graf const *graf, int keresettid); 
```
#### Bemenet
	A függvénynek két bemenete van, a gráf amin keres és a keresett ID.

#### Működés
	A függvény végigiterál a csúcsok láncolt listáján és ellenőrzi az id-t. 

#### Kimenet
	A függvény visszatér a megtalált csúcs pointerével. Amennyiben az nem létezik NULL pointerrel tér vissza

### Csúcs hozzáadás a gráfhoz

```c
int csucsHozzad(Graf *graf, int id);
```

#### Bemenet
	A függvénynek két bemenete van, a gráf és a hozzáadandó csúcs Id-ja.


#### Működés
	A Függvény dinamikusan foglal memóriaterületet az új csúcsnak
	A függvény megkeresi az utolsó elemét a csúcslistának és annak a *kov címére beállítja a lefoglalt címet.

#### Hibakezelés
	A Függvény visszatér 2-vel ha
		Üres gráf címet kap
		Létező csúcsot próbált hozzáadni a felhasználó
	A Függvény visszatér 0-val ha
			Nem sikerült a memóriafoglalás

#### Kimenet
	A függvény visszatér 1-el ha sikerült a foglalás.

### Él hozzáadás

```c
int elHozzaad(Graf *graf, int forras, int cel, double suly);
```

#### Bemenet
	A függvény megkapja a gráf címét, az induló csúcs azonosítóját, a cél csúcs azonosítóját, az él súlyát.
#### Működés
	Megkeresi a forrás csúcsot (csucsFind).
	Dinamikusan memóriát foglal az élnek, beállítja az adatait
	Végigiterál a *szomszédok láncolt listán és megkeresi az utolsó elemét, annak a *kov pointerére beállítja a foglalt címet.

#### Hibakezelés
	  A Függvény visszatér 2-vel ha
		Üres gráf címet kap
		Negatív súlyt kap
	A Függvény visszatér 0-val ha
			Nem sikerült a memóriafoglalás

#### Kimenet
	 Ha sikeres a hozzáadás visszatér 1-el


### Gráf Megjelnítés v1
```c
void printGraf(const Graf *graf);
```
#### Bemenet
	 Egy bemenete van, a gráf pointere.

#### Működés
	 Végigmegy a gráf csúcsain, csúcsonként az éleken is végigmegy és kíírja azok adatait.

#### Kimenet
	Visszatérési értéke nincs, a consolera printel.


//page
## menu - Modul

A menü modul egy függvényt tartalmaz:

```c
void initMenu(Graf *graf);
```

A Menü a terminálból kezelhető.
Ott megjeleníti a következő menüt, majd beolvassa a felhasználót, hogy mit szeretne csinálni.
```
========== GRAFKEZELO ==========

1. BFS bejárás
2. DFS bejárás
3. Dijkstra
4. Gráf adatainak megjelenítése
5. Kilépés

Választás:
```

Bemenet után, lefuttatja a kívánt algoritmust.

