F.C. Manager v1.0 Aplha #1
==========================


1. What is it?

This is an application designed for secretaries/managers of
football teams to use to manage their affairs. It is really
nothing more than a glorified database with a few extra
visuals elements thrown in.

It allows you to keep a database of club members, fixtures,
opponents and referees (these last two are more for making
the entering of fixtures easier and keeping track of stats).
You can also keep track of the money your club has recieved
and spent, and find out which players owe what.

The only "feature" which you couldn't do with Access or Excel
is the team sheet, which is a graphical way of selecting a
team and visualising your game plan, not that we ever had one!


2. Licence.

This is freeware, i.e. no charge, pass it onto who you like etc.
This also means that you use it entirely at your own risk! I
won't be held responsible for any damage you do to your 
machine, limbs etc. That said, I hope that I have developed it
well enough that you'll not have any problems, but with software
you never know, lets be careful out there.


3. The state of development.

This is (as you should gather from its alpha status) really only
the early stages, it is very much work in progress. It is very
fragile in some areas, e.g. deleting players who have some
income associated with them. The following are the main areas of
missing functionality.

- Teams sheets, you can pop the dialog up and change the formation,
  that's it though.
- Statistics, you can't add custom stats types.
- Reports, none done yet.
- Printing, partially works, I am working on that at the moment.
- Importing data, only from data exported by this app.
- Expenses, you can only enter a fixed amount, or none.

The build is a debug build and contains wadges of extra code to
check its internal state. This means that its slow, and you will
probably see a message boxed labeled "Assert Failed" if you did
something unexpected. If you ignore this (press 'no') the app
may crash or carry on without any problems, it depends on what went
wrong. Also the file format may (and probably will) change as
things proceed, don't expect to be able to load older files with
newer releases.

I have written and tested it only on Windows 2000. It should work
on all Win32 platforms, i.e. 95/98/ME/NT/2K. However I have used some
features which may not work on very early releases of Win95 unless
IE v3 or later is installed.

If you're looking at this app and are interested in it, let me know,
especially if you have some suggestions for additional features or
changes to its behaviour. It is based soley around the way I used
Excel to manage my existing club and I probably do it differently
to you, or maybe I don't record things you do. All feedback is
welcome.

I can't promise as to when (or even if) I will finish this app. It
is only developed in my spare time, however if enough people seem
interested it will give me more of an incentive to actually get it
done.


4. The manual.

There isn't one...yet. I have supplied a sample file to play with,
but I'm afraid you'll have to work out how to use the app yourself.
If i've done a reasonable job you should be able to guess how most of
it works. One very problematic area is how payments are recorded
and associated with an item on the balance sheet. You can only edit
them this way, not through the 'subs' view, but I hope to make it
more user-friendly.

5. Contact details.

I can be reached at gort@cix.co.uk or chris.oldwood@ntlworld.com.
A web site is planned for all my various "things"and will appear
at http://www.cix.co.uk/~gort in the near future.


Chris Oldwood
18 Jan 2001
