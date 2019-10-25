<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" lang="" xml:lang="">
<head>
  <meta charset="utf-8" />
  <meta name="generator" content="pandoc" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes" />
  <title>raport_list03</title>
  <style type="text/css">
      code{white-space: pre-wrap;}
      span.smallcaps{font-variant: small-caps;}
      span.underline{text-decoration: underline;}
      div.column{display: inline-block; vertical-align: top; width: 50%;}
  </style>
</head>
<body>
<ul>
<li>Zadanie 1</li>
</ul>
<p><em>(5pt)</em> Wytłumacz jakie pliki zawierają katalogi <strong>/dev</strong> oraz <strong>/proc</strong>. Wykorzystując polecenie <strong>dd</strong> odczytaj pierwszy sektor z dysku głównego (uwaga na prawa dostępu) lub podpiętego pendrive'a i wyświetl przez <strong>hexdump -C</strong>. Z katalogu <strong>proc</strong> wyświetl informacje o pamięci, procesorze i partycjach. </p>

<ol type="1">
<li>Katalogi:</li>
</ol>
<ul>
<li><strong>/dev -</strong> od devices, znajdujące się w nim pliki to pliki pośredniczące w komunikacji system- urządzenia. Nie są to faktyczne pliki na dysku.</li>
<li><strong>/proc –</strong> od processes, jest katalogiem wirtualnym, znajdują się w nim dane o aktualnie uruchomionych procesach</li>
</ul>

<ol type="1">
<li>Sektor i pendrive hexump</li>
</ol>
<ul>
<li>pierwszy sektor dysku głównego </li>
</ul>
<ol type="1">
</ol>

<ul>
<li>pendrive</li>
</ul>
<p>sudo dd if=/dev/disk/by-id/usb-Kingston_DataTraveler_3.0_1831BFBBBED1B310A95F0050-0\:0-part1 bs=1 count=1k | hexdump -C</p>

<ol type="1">
<li>Informacje z katalogu <em>proc cd proc &gt; ls - l | grep partition/ mem/ cpu</em> &gt; cat</li>
</ol>
<ul>
<li><em>partycje</em> – cat proc/partitions</li>
<li><em>pamięć</em> <em>- </em> cat proc/meminfo</li>
<li>procesor – <strong>cat proc/cpuinfo</strong></li>
</ul>

<ul>
<li>Zadanie 2</li>
</ul>
<p><em>(5pt)</em> Zapoznaj się z programem <strong>ps</strong> (<strong>man ps</strong>). Naucz się posługiwać tym programem, aby umieć sprawdzać co najmniej istnienie i parametry wybranych procesów (PID procesu i rodzica, stan procesu, priorytet, nice, ilość pamięci, zużycie czasu procesora). Uruchom też kilka terminali pokaż jakie urządzenie tty wykorzystują. Wykonując komendę <strong>ps axjf</strong> pokaż wszystkie procesy które podpięte są do tych terminali (kolumna TTY). </p>

<ol type="1">
<li>Ps – wyświetla informacje o wyselekcjonowanych aktywnych procesach.</li>
<li>Pid po nazwie Ps -C nazwa</li>
<li>ppid po pid X ps -o ppid=,tty= -p X </li>
<li>pid po ppid ps -f --ppid X</li>
<li>sort ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head</li>
<li>morderstwo procesu <strong> kill -9 2583</strong></li>
<li>priorytet<strong> ps -p 8238 -o priority=</strong></li>
<li>nice<strong> ps -p 8238 -o nice=</strong></li>
<li>podpięcia<strong> ps-t </strong></li>
<li>pamięć i zużycie cpu<strong> ps -p 4445 -o %mem=,%cpu=</strong></li>
<li>select tylko konkretnego terminalu<strong> ps axjf |grep pts/3</strong></li>
</ol>


<ul>
<li>Zadanie 3</li>
</ul>
<p>Wytłumacz każdy z powyższych kroków. Co oznaczają opcje <strong>-Wall</strong> oraz <strong>-pedantic</strong>? Zobacz <strong>man gcc</strong>. //man grep^</p>

<ol type="1">
<li><strong>-Wall</strong> - włącza konkretne flagi ostrzegawcze (-Wunused-parameter,-Wno-format-extra-args, ...)</li>
<li>-pedantic – powoduje wyświetlanie ostrzeżeń przed użyciem alternatywnyc słów kluczowych</li>
</ol>


<ul>
<li>Zadanie 4</li>
</ul>
<p><em>(5pt)</em> Pokaż na przykładzie (np. <strong>sleep 1000</strong>, <strong>sleep 1001</strong>, ...) zarządzanie zadaniami wykorzystując <strong>&lt;polecenie&gt; &amp;</strong> - uruchamianie w tle (background) oraz <strong>jobs, fg, bg, kill</strong> oraz <strong>^Z</strong>. Uruchom kilka zadań w tle i pokaż jak można nimi zarządzać, czyli zatrzymywać, wznawiać oraz kończyć ich działanie. Pokaż jak uruchomione zadanie (nie w tle), można w czasie działania uruchomić w tle np. wykonując komendę <strong>sleep 100</strong> (bez &amp;) w czasie działanie przełącz je do działania w tle.</p>

<ol type="1">
<li>sleep 1000 &amp; sleep 1001 &amp; sleep 1002 </li>
<li><strong>jobs</strong> – wyświetla zadania</li>
<li>fg – przesuwa na front </li>
<li>bg – przesuwa zadanie na tryb w tle</li>
<li><p>kill -morduje proces // tutaj warto skorzystać z ps -t i wtedy killem kill -9 pid</p></li>
</ol>
<ul>
<li>Zadanie 5</li>
</ul>
<p><em>(5pt)</em> Poleceniem <strong>mkfifo</strong> (<strong>man mkfifo</strong>) utwórz potok nazwany (ang. <em>named FIFO</em>). Wywołując polecenie <strong>cat</strong> w różnych terminalach spowoduj wpisywanie danych do potoku przez jeden(ne) proces(y), i odczytywanie i wyświetlanie ich przez inne. Zaobserwuj, kiedy polecenie <strong>cat</strong> czytające z potoku czeka na więcej danych, a kiedy kończy pracę. Analogicznie, kiedy czeka na więcej danych (z klawiatury) polecenie <strong>cat</strong> piszące do potoku? </p>

<ol type="1">
<li>Mkfifo x.pipe</li>
<li>cat &lt;&gt; x.pipe wyświetla potok na bieżąco</li>
<li>multiwpisywanie do jednego naraz działa poprawnie</li>
<li>multiwyświetlanie terminale walczą o konkretne sygnały, wyświetlają w sumie całość</li>
<li> przyadtne<strong> </strong><em><em><strong>for i in `seq 20 30` ; do echo $i ; sleep 1; done &gt; namedfifo.pipe</strong></em></em></li>
</ol>

<ul>
<li>Zadanie 6</li>
</ul>

<ul>
<li>Zadanie 7</li>
</ul>
<p>touch ./”nazwapliku”</p>
</body>
</html>
