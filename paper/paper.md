---
title: 'Ethowatcher.OpenSource: improving quality control and blind procedures during categorical and morphologic/kinematic extraction of behavioral data in laboratory animals.'
tags:
  - video-tracking
  - image segmentation
  - behavioral recording
  - intra-rater reliability
  - blind-to-condition studies
  - image processing

authors:
  - name: João Antônio Marcolan
    orcid: 0000-0001-8368-0213
    affiliation: 1
  - name: José Marino Neto
    orcid: 0000-0001-5090-8867
    affiliation: 1
affiliations:
 - name: Institute of Biomedical Engineering, EEL-CTC, Federal University of Santa Catarina, 88040-900 Florianópolis SC, Brazil 
   index: 1
date: 26 June 2021
bibliography: paper.bib
---

# Summary

In 2012, we presented a freely available software (EthoWatcher ; Crispim-Junior et al, 2012 ) developed to support ethography, object tracking and extraction of kinematic variables from digital video files of lab animals. Proprietary? C++, limited video formats, Despite its limitations in tools and technology, this software has been increasingly used since then in studies of animal behaviors in disparate fields as behavioral pharmacology, physiology, psychology, and ecology.
 
User´s suggestions and urges to collaborate, increasingly demands for tools to improve data reproducibility new collaborative technologies and machine vision algorithms. Here we present a new version of this software, the Ethowatcher-OS, that adds tools designed to:

- 1) improve bulk video-file management, permitting the use of a large range of prerecorded video-file characteristics, origins, and codecs, 
- 2)	allow for rapid and safe use of blind-to-condition categorical transcriptions, that are simultaneous with tracking and were facilitated by using buttons in the screen to enter categories
- 3)	Categories associated frame-by-frame to tracking, morphological and kinematic attributes of animal’s image (extracted using machine vision algorithms), allowing to build databanks suitable for machine learning processing
- 4)	controls and corrections for artifacts of tracking 
- 5)	routines to examine intra- and inter-observer reliability throughout observers training and during valid data gatherings, using Cohen´s Kappa (K), Fleiss’s K statistics and some corollary measures (bias, prevalence, Kmax , etc.) of agreement  
- 6)	provide extended capabilities of temporal and spatial segmentation of categorical, morphological and kinematic data extracted from video, as well as offer outputs for semi-markov chains-based sequential analysis, and
- 7)	developed and made available through an open-source platform cooperative environment to allow for continuous collaborative improvements or addition of data extraction and data analysis algorithms. [@spink2001ethovision] [@lind2005validation]  



# Acknowledgements


The present study was supported by ..... an JAM received CAPES MSc fellowships. 



# References