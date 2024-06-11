#### 314638669 | Barak10101998@gmail.com
# תכנות מערכות מטלה 3 - קאטן
___
הפעלה:
---
לקימפול והרצת הדמו `make catan`

לקימפול והרצת הטסט `make catanTest`

הנחות לחוקי המשחק
---
- נניח כי הסדר של השחקנים ידוע מראש וכי כל משחק אך ורק בתורו (אם שחקן א סיים לשחק המימוש לא ידוע כי תורו של שחקן ב)
- בתחילת המשחק נניח שלא מגרילים את סדר האדמות במפה ואת המספרים
- בלקיחת קלף מקופת קלפי הקידום נניח כי היא אם שחקן יבקש קלף הוא יקבל כל עוד הוא קיים בחפיסה
- בDemo נניח כי לא מגרילים מספר והמספר נבחר מראש לשם ההדגמה
- נניח כי שחקן שמקבל קלף קידום יכול לשחק איתו בתורו

מימוש המשחק
---

למשחק שלוש מחלקות עיקריות:
- מחלקת השחקן `Player.hpp`
- מחלקת הלוח `Board.hpp`
- מחלקת הקאטן `Catan.hpp`
- מחלקות הקלף והרכוש `Card.hpp` `Property.hpp`

מימוש מחלקת הלוח `Board.hpp`
-
שדות ומתודות פרטיים:
- גרף הלוח `Graph _graph`

  מחלקת הגרף `Graph.hpp` היא מחלקה המייצגת מטריצת שכנויות מסוג
  .`vector<vector<char>> _adjMatrix`
    כל קודקוד במטריצה מייצג מקום שאפשר לבנות בו יישוב או עיר, כל צלע במטריצה מייצגת מקום שאפשר לבנות בו דרך
   נשייך לכל שחקן מספר מזהה מסוים x מסוג char ונגדיר:
  - כאשר בקודקוד קיים הערך 0 - הקודקוד פנוי לבנייה של יישוב
  - כאשר בצלע קיים הערך 0 - לא ניתן לבנות בה דרך והצלע לא נמצאת במשחק
  - כאשר בצלע קיים הערך 1 - הצלי פנויה לבנייה בה דרך
  - כאשר בצלע קיים הערך x - שחקן בעל מספר מזהה x בנה שם דרך
  - כאשר בקודקוד קיים הערך x+1 - שחקן בעל מספר מזהה x בנה שם יישוב
  - כאשר בקודקוד קיים הערך x+2 - שחקן בעל מספר מזהה x בנה שם עיר
  
- תשע עשרה האדמות של המשחק `Land _land[19]`
  - מחלקת האדמה `Land.hpp` היא מחלקה המייצגת אדמה שבגבולותיה שוכנים ערים ויישובים
  למחלקה קיים שדה המשושה `Hexagon _hexagon` המייצג את המשושה בעל ששת הקודקודים להם האדמה משויכת
  - למחלקה קיים ערך מספרי המייצג את המספר הרנדומלי מ2-12 המשוייך אליה `int _value`
  - `string _resource` למחלקה קיים שדה של שם האדמה `string _landType` ושם המשאב אותו היא מספקת
  - למחלקה קיימת מתודה האם קודקוד מסוים נמצא על האדמה שלי `sitOn(int)`

- קופת קלפי הקידום של המשחק 
`GameSet<DevelopmentCard> _developmentCards`, על מחלקה זאת נרחיב בהמשך

- איתחול הלוח `init()`

מתודות ציבוריות:
- האם שחקן יכול לבנות נכס במיקום מסוים `canBuild(string,id,int,int,int)`
- בניית נכס במיקום מסוים `build(string,char,x,y)`
- קבלת משאבים לפי מספר מזהה של שחקן והמספר שמראה הקוביה `getResources(char,int,int)`
- משיכת קלף קידום מהקופה `getDevelopmentCard(string)`

מימוש מחלקות הקלף והרכוש `Card.hpp` `Property.hpp`
-
מחלקות אלה מייצגות מספר של אובייקטים באובייקט אחד, כלומר מחלקת הקלף מייצגת חפיסת קלפים שווים ומחלקת הרכוש מייצגת מספר רב של מבנים דומים,
לצורך כך שני המחלקות יורשות ממחלקות `Countable.hpp` - ניתן למספר, `Identifiable.hpp` - ניתן להבחין
- מימוש מחלקת `Countable.hpp`
  - שדה פרטי המייצג את מספר האובייקטים `int _amount`
  - מתודה ציבורית המחזירה את המספר `size()`
  - מתודות ציבוריות המוסיפות ומחסירות את המספר `add(int)` `remove(int)`
  - מתודה המאפסת את המספר c`lear()`
- מימוש מחלקת `Identifiable.hpp`
  - מחלקה זאת מחזיקה שדה פרטי של שם string _type ומתודה ציבורית המחזירה אותה `getType()`

### מימוש מחלקת `Property.hpp`
שדות פרטיים:
- מספר המייצג כמה נקודות ניצחון שווה הרכוש `int _pointsVal`
- שדה המייצג את העלות של קניית הקלף `GameSet<ResourceCard> _cost`

מתודות ציבוריות:
- מתודה המחזירה את נקודות הניצחון שווה הרכוש `getWinPoints()`
- מתודה המחזירה את העלות של קנייה של רכוש `getCost()`

### מימוש מחלקת `Card.hpp`
מימוש המחלקה לא מיוחד, קיימות לו שני מחלקות שיורשות ממנו מחלקת ResourceCard ומחלקת DevelopmentCard המייצגות את הקלפים השונים במשחק.

### מימוש מחלקת `ResourceCard.hpp`
למחלקת ResourceCard אין עוד מתודות ושדות שהיא ממשת, הבנאי שלה בודק אם הקלט תקין

### מימוש מחלקת `DevelopmentCard.hpp`
מחלקת DevelopmentCard ממשת מתודות ושדות נוספים מכיוון שקיימת לה פונקציונליות נוספת:

שדות פרטיים:
- שדה המייצג את העלות של קניית הקלף `GameSet<ResourceCard> _cost`

מתודות ציבוריות:
- בנאי הקולט אם הקלט תקין
- מתודה המחזירה את העלות של קנייה של רכוש `getCost()`


מימוש מחלקת השחקן `Player.hpp`
-
שדות פרטיים:
- שם השחקן `string _name`
- מספר מזהה של השחקן `char _id`
- מספר נקודות הניצחון של השחקן `int _winPoints`
- מספר הסיבוב בו נמצא השחקן כאשר 0 הוא הסיבוב הראשון `int _turnCounter`
- האם תור השחקן כרגע `bool _isTurn`
- כמה קלפי אבירים חשפנו `int _armySize`
- חפיסת הקלפים בראשות השחקן `GameSet<Card> _cards`
- כל הרכוש של השחקן שנועד לבנייה `GameSet<Property> _properties`
  
  מימוש מחלקת `GameSet.hpp`
  
  מחלקה זו היא מבנה נתונה גנרי `template <typename T> GameSet<T> (...)`
  מבנה נתונים זה מדמה חפיסה של חפיסות קלפים שונות:
  - המחלקה מחזיקה כשדה פרטי מערך מסוג גנרי `vector<T> _set`
  
  מתודות ציבוריות:
  - `template<typename P> GameSet(GameSet<P>&)` בנאי המשמש לקאסטינג למחלקה אחרת (רק למחלקות היורשות גם Countable ו Identifiable)
  - מתודה המוסיפה חפיסה חדשה `add(string,int)`
  - מתודה המחפשת חפיסה `search(string)`
  - מתודה המחסירה מחפיסה `remove(string,int)`
  - מתודה המחזירה חפיסה באינדקס מסוים `getAt(int)`
  - מתודה המחזירה את הגודל של המערך `size()`
  - מתודה מנקה את המערך `clear()`
  - מתודה מחזירה את המערך כמחרוזת `toString()`
  - מתודה המחזירה האם תת מערך מוכל בו `contains(GameSet<T>&)`
  - אופטור חיסור שווה - מוריד איברים מהמערך`operator-=(GameSet<T>&)`
  - `operator+=(GameSet<T>&)`אופרטור פלוס שווה- מוסיף איברים למערך

- מתודה המשתמשת בקלף פיתוח של השחקן `useDevelopmentCard(string)`
- מתודה הבודקת האם השחקן יכול לשלם בקלפים מסוימים `canPay(GameSet<Card> &)`
מתודות ציבוריות:
- בנאי בונה ובנאי הורס
- מחזיר את השם של השחקן `string getName()`
- מחזיר את מספר המזהה של השחקן `getID()`
- מוסיף נקודות ניצחון לשחקן `addWinningPoints(int)`
- מחסיר נקודות ניצחון לשחקן `removeWinningPoints(int)`
- מחזיר את נקודות הניצחון של השחקן `getWinPoints()`
- השחקן מתחיל את התור `startTurn()`
- השחקן מסיים את התור `endTurn()`
- מחזיר את הסיבוב שהשחקן נמצא בו כרגע `getTurn()`
- `pay(GameSet<Card> &)`השחקן משלם בקלפים 
- השחקן מקבל קלפים `pay(GameSet<Card> &)`
- השחקן מוריד חצי מקלפי המשאבים שלו `removeHalf(GameSet<ResourceCard>&)`
- לבנות `build(string,Board&,x,y)`
- לסחור`trade(GameSet<Card>,Player*,GameSet<Card>)`
- לקנות קלף פיתוח `buyDevelopmentCard(string,Board&)`
- לזרוק קובייה `rollDice()`
- להשתמש בקלף שנת שפע `useWealthyYearCard(string,string)`
- להשתמש בקלף בנאי `useBuilderCard(int,int,int,int)`
- להשתמש בקלף מונופול `useMonopolyCard(string,Player*,Player*)`
- להשתמש בקלף אביר `useKnightCard()`
- החזרת השחקן כמחרוזת `toString()`
- אופרטור הדפסה לשחקן `operator<<(ostream,Player*)`

מימוש מחלקת הקאטן `Catan.hpp`
-
מחלקת הקאטן היא מחלקה המקשרת בין השחקן ללוח ורוב המתודות שלה יהיו קשורות לכל השחקנים וללוח עצמו

שדות פרטיים:
- לוח המשחק `Board _board`
- מערך השחקנים `Player* _turnOrder[3]`
- שחקן בעל הצבא הכי גדול `Player* largestArmy`
- גודל הצבא הכי גדול `int _largestArmy`

מתודות ציבוריות:
- החזרת לוח המשחק `getBoard()`
- חלוקת משאבים לכל השחקנים לפי מספר רנדומלי `distributeResources(int)`
- בדיקת הצבא הכי גדול `checkLargestArmy(Player*,int)`
- הדפסת המנצח אם בכלל `printWinner()`
