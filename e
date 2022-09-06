CLOSEDIR(3)                                                             Linux Programmer's Manual                                                             CLOSEDIR(3)

NNAAMMEE
       closedir - close a directory

SSYYNNOOPPSSIISS
       ##iinncclluuddee <<ssyyss//ttyyppeess..hh>>

       ##iinncclluuddee <<ddiirreenntt..hh>>

       iinntt cclloosseeddiirr((DDIIRR **_d_i_r_p));;

DDEESSCCRRIIPPTTIIOONN
       The  cclloosseeddiirr()  function closes the directory stream associated with _d_i_r_p.  A successful call to cclloosseeddiirr() also closes the underlying file descriptor associated
       with _d_i_r_p.  The directory stream descriptor _d_i_r_p is not available after this call.

RREETTUURRNN VVAALLUUEE
       The cclloosseeddiirr() function returns 0 on success.  On error, -1 is returned, and _e_r_r_n_o is set appropriately.

EERRRROORRSS
       EEBBAADDFF  Invalid directory stream descriptor _d_i_r_p.

AATTTTRRIIBBUUTTEESS
       For an explanation of the terms used in this section, see aattttrriibbuutteess(7).

       ┌───────────┬───────────────┬─────────┐
       │IInntteerrffaaccee  │ AAttttrriibbuuttee     │ VVaalluuee   │
       ├───────────┼───────────────┼─────────┤
       │cclloosseeddiirr() │ Thread safety │ MT-Safe │
       └───────────┴───────────────┴─────────┘
CCOONNFFOORRMMIINNGG TTOO
       POSIX.1-2001, POSIX.1-2008, SVr4, 4.3BSD.

SSEEEE AALLSSOO
       cclloossee(2), ooppeennddiirr(3), rreeaaddddiirr(3), rreewwiinnddddiirr(3), ssccaannddiirr(3), sseeeekkddiirr(3), tteellllddiirr(3)

CCOOLLOOPPHHOONN
       This page is part of release 5.05 of the Linux _m_a_n_-_p_a_g_e_s project.  A description of the project, information about reporting bugs, and the latest version of  this
       page, can be found at https://www.kernel.org/doc/man-pages/.

                                                                                2015-08-08                                                                    CLOSEDIR(3)
