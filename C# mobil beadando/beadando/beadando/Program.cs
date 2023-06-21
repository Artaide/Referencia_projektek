using System;
using System.Collections.Generic;

namespace InfinityMaze_Console
{
    public class Szoba
    {
        public List<string> irányok = new List<string>();
        public int irányszám;
        public List<string> talált = new List<string>();

        public void Megjelenít()
        {
            Console.WriteLine(irányok);
        }
    }

    public class Inventory
    {
        public bool scan_available = true;
        public int goldcoins = 10, hp = 100;
        public List<string> tárgyak = new List<string>();

        public void Status()
        {
            Console.WriteLine("Arany: " + goldcoins + " | életerő " + hp + "/100");
            foreach (string item in tárgyak)
            {
                Console.WriteLine(item);
            }
        }
    }

    public class Szörny
    {
        public string[] szörnyek = { "Csontváz", "Minotaurusz", "Sárkány", "Mutáns Pók", "Ork"};
        public int[] szörny_erőszintek = { 1, 2, 3, 2, 1 };
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Végtelen Útvesztő");
            SzabályMegjelenítés();
            Console.WriteLine("Press Any Button To Continue");
            Console.ReadKey();
            MainMenu();
        }

        static void MainMenu()
        {
            int n = 0;
            Szoba szoba = new Szoba();
            Inventory player = new Inventory();
            while (player.hp > 0)
            {
                Console.Clear();
                Random random = new Random();
                int direction_num = random.Next(1,3);

                switch (direction_num)
                {
                    case 1:
                        Console.WriteLine("1 irányban lehet előre haladni");
                        Console.WriteLine("    [ ]    ");
                        szoba.irányok.Add("    [ ]    ");
                        szoba.irányszám = 1;
                        break;
                    case 2:
                        Console.WriteLine("2 irányban lehet előre haladni");
                        Console.WriteLine("[ ]   [ ]");
                        szoba.irányok.Add("[ ]   [ ]");
                        szoba.irányszám = 2;
                        break;
                    case 3:
                        Console.WriteLine("3 irányban lehet előre haladni");
                        Console.WriteLine("[ ]  [ ]  [ ]");
                        szoba.irányok.Add("[ ]  [ ]  [ ]");
                        szoba.irányszám = 3;
                        break;
                }

                Console.Write("Parancs: ");
                string cmd = Console.ReadLine();

                switch (cmd)
                {
                    case "előre":
                        int i = -1;
                        bool hiba = true, megvan = false;
                        Szörny szörny = new Szörny();
                        Random tmp_id = new Random();
                        int tmp = tmp_id.Next(1, 5);
                        string tmp_monster = szörny.szörnyek[tmp];

                        if (direction_num == 1)
                        {  
                            while (!megvan)
                            {
                                i++;
                                if (szörny.szörnyek[i] == tmp_monster)
                                {
                                    megvan = true;
                                }
                            }
                            Console.WriteLine("Útban áll egy " + tmp_monster + "\nMit teszel?" );
                            while (hiba)
                            {
                                cmd = Console.ReadLine();
                                if (cmd == "harc")
                                {
                                    tmp = tmp_id.Next(1, 10);
                                    Console.WriteLine("legyőzted, találtál " + tmp + " aranypénzt, de elveszítettél " + tmp * szörny.szörny_erőszintek[i] + " életerőpontot.");
                                    player.goldcoins += tmp;
                                    player.hp -= tmp * szörny.szörny_erőszintek[i];
                                    player.scan_available = true;
                                    hiba = false;
                                }
                                else if (cmd == "elszökés")
                                {
                                    Console.WriteLine("elszöktél, de elvesztettél 5 aranypénzt.");
                                    player.goldcoins -= 5;
                                    hiba = false;
                                }
                                else if (cmd == "parancsok")
                                {
                                    SzabályMegjelenítés();
                                    hiba = false;
                                }
                                else if (cmd == "státusz")
                                {
                                    player.Status();
                                }
                                else
                                {
                                    Console.WriteLine("Ismeretlen parancs");
                                }
                            }
                        }
                        else if (direction_num == 2)
                        {
                            Console.WriteLine("Melyik irányba?");
                            cmd = Console.ReadLine();
                            if (cmd == "1" || cmd == "bal" || cmd == "balra")
                            {
                                while (!megvan)
                                {
                                    i++;
                                    if (szörny.szörnyek[i] == tmp_monster)
                                    {
                                        megvan = true;
                                    }
                                }
                                Console.WriteLine("Útban áll egy " + tmp_monster + "\nMit teszel?");
                                while (hiba)
                                {
                                    cmd = Console.ReadLine();
                                    if (cmd == "harc")
                                    {
                                        tmp = tmp_id.Next(1,10);
                                        Console.WriteLine("legyőzted, találtál " + tmp + " aranypénzt, de elveszítettél " + tmp * szörny.szörny_erőszintek[i] + " életerőpontot.");
                                        player.goldcoins += tmp;
                                        player.hp -= tmp * szörny.szörny_erőszintek[i];
                                        hiba = false;
                                    }
                                    else if (cmd == "elszökés")
                                    {
                                        Console.WriteLine("elszöktél, de elvesztettél 5 aranypénzt.");
                                        player.goldcoins -= 5;
                                        hiba = false;
                                    }
                                    else
                                    {
                                        Console.WriteLine("Ismeretlen parancs");
                                    }
                                }
                            }
                            else if (cmd == "2" || cmd == "jobb" || cmd == "jobbra")
                            {
                                tmp = tmp_id.Next(1,20);
                                if (tmp % 2 == 0)
                                {
                                    Console.WriteLine("Egy kereskedővel találod magad szemben, vásárolsz valamit?");
                                    cmd = Console.ReadLine();
                                    if (cmd == "igen")
                                    {
                                        Console.WriteLine("Vásárolható tárgyak: ");
                                        Console.WriteLine("1:[HP Potion (-5 arany, +5 hp)] 2:[valami1] 3:[valami2]");
                                        cmd = Console.ReadLine();
                                        switch (cmd)
                                        {
                                            case "1":
                                                Console.WriteLine("HP Potion megvásárolva");
                                                player.goldcoins -= 5;
                                                player.hp += 5;
                                                break;
                                            case "2":
                                                Console.WriteLine("valami történt");
                                                break;
                                            case "3":
                                                Console.WriteLine("valami történt");
                                                break;
                                            default:
                                                Console.WriteLine("Ismeretlen Parancs.\nAz elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                                                break;
                                        }
                                    }

                                }
                                else
                                {
                                    Console.WriteLine("Zavartalanul továbbhaladsz.");
                                }
                            }
                        }
                        Console.WriteLine("Továbblépés...");
                        n++;
                        break;
                    case "keresés":
                        if (player.scan_available == true)
                        {
                            Random talált_arany = new Random();
                            tmp = talált_arany.Next(1, 10);
                            Console.WriteLine("Találtál " + tmp + " aranyat. Harcolnod kell egyszer, hogy használhasd ezt a parancsot újra");
                            player.goldcoins += tmp;
                        }
                        else
                        {
                            Console.WriteLine("Jelenleg nem használhatod ezt a parancsot.");
                            Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        }
                        n++;
                        break;
                    case "tárgyhasználat":
                        break;
                    case "harc":
                        Console.WriteLine("Nincs mivel harcolni");
                        Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        n++;
                        break;
                    case "elszökés":
                        Console.WriteLine("Nincs mitől elszökni");
                        Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        n++;
                        break;
                    case "státusz":
                        player.Status();
                        Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        n++;
                        break;
                    case "szabályok":
                        SzabályMegjelenítés();
                        Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        n++;
                        break;
                    default:
                        Console.WriteLine("Ismeretlen parancs");
                        Console.WriteLine("Az elpazarolt idő alatt lehetséges, hogy átrendeződött az Útvesztő, és más lehetőségek állnak előtted, mint egy pillanattal ezelőtt.");
                        n++;
                        break;
                }
                Console.ReadKey();
            }
            Console.WriteLine("Meghaltál");
            Console.WriteLine("Túlélt körök száma: " + n);
        }

        static void SzabályMegjelenítés()
        {
            Console.WriteLine("Parancsok: előre, keresés, tárgyhasználat, harc, elszökés, igen, nem, státusz");
            Console.WriteLine("Szabályok:\n- keresni csak 1-szer tudsz szobánként, és harcolnod kell egy keresés után, ha szeretnél megint keresni.");
            Console.WriteLine("- ha harcolsz, pénzt szerzel, de életerőt veszítesz");
        }
    }
}
