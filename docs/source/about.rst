.. _about:

=====
About
=====

.. _why:

Why?
====

For most engineering and scientific applications that come across my
desk, it's a case of "prototype in MATLAB or Python, rewrite in C++".
But:

  * I'm long past bothering with MATLAB (there's no credible CI/CD options, no sensible test framework, the slug size of the runtime library is 3.7Gb with a huge memory requirement making it undeployable on any sensible server, the license costs would make Bezos flinch, mex interfaces are grossly unwieldy, etc etc etc etc).

  * I'm getting really really sick of writing the damn code twice.

  * Most of my engineering and science apps are now getting deployed to cloud services. So displaying natively generated figures like from matplotlib in-browser is a nightmare.

What I need is a solution where I can prototype straight into a language
which is fast, capable and has a pretty good ecosystem of third party
libraries to help me.

Now, with:

  * the great improvements to C++ in the C++11 and 14 standards (which make it much easier to handle threading and generally connect APIs of various libraries together),

  * availability of libraries like Eigen, cpr, ceres-solver, Intel MKL (I could go on and on),

  * great utilities like googletest and Cmake to remove all the old-skool build and test agony...

C++ is really getting there. The one thing missing is a plotting
library, which allows me to:

  * quickly and easily prototype new algorithms (visually diagnose what's wrong etc etc)

  * display analysis results on the web

  * produce the same figures on different platforms

  * save publication quality figures easily

In all the other languages I use, I now use ``plotly`` to do those
things. So now it's here for C++ too.


.. _about_plotly:

About Plotly
============

**cpplot** is based on the plot.ly json schema for figures and charts.


.. _figure_json_schema

Figure json schema
------------------

At the core of plotly is a set of open specifications for JSON data
which can be rendered into various figure types. The plotly team
have hung a lot of services and offerings around it,
but basically everything boils down to a `json schema <https://plotly.com/chart-studio-help/json-chart-schema/>`__.
**cpplot** helps generate JSON which is compliant with that schema.


.. _plotly_offline:

Plotly Offline
--------------

``Plotly.js`` is an excellent javascript library for rendering figures, which can
be used offline or in any third party app. This is what's used by the browser viewer.


.. _plotly_online:

Plotly Online
-------------

Plot.ly have a range of online services, and anything produced by **cpplot** will be
importable there, since it's compliant with their schema.

I'm not a marketing person for plotly, so how to do that is out of scope here (check their docs)!!

I have some code using the Plotly API (`see online.h <https://github.com/thclark/cpplot/blob/458d26f99aa4298e7260bb5da65ba7915f098f5f/source/online.h#L160>`__ ),
which might be the very early beginning of a client SDK for C++,
enabling direct manipulation of online data. However, I have very little
appetite for this (I personally don't use plotly online, because I've
found the support to be appalling in the past) but collaborators
committed to developing and maintaining that would be welcome. File an issue if you're interested.


