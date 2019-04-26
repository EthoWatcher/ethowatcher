

# Introduction
The Ethowatcher OS allow the classical behavioral analysis also to extract kinematic and morphological descriptors (ie. tracking). The way the program organizes the data resulting from the study makes it possible to perform a series of analyzes that are already discussed in the state of the art but are not found in practice by other programs of the same genre (eg, concordance analysis, sequential analysis). In addition, the organization of the data will allow the use of artificial intelligence algorithms.

# Tools developed
The Ethowatcher OS modules were divided into the preparation tools for behavioral transcription, kinematic and morphological behavioral transcription (TCCM) and categorical behavioral transcription (TCC) and Transcript Analysis tools

# The preparation tools

The preparation tools allow you to record important information on animal behavior analysis. This group of tools has the module of:
- Video registration, which allows to register the variables essential for normal and blind categorical analysis, calibrate the algorithm for tracking and extraction of kinematic and morphological variables and noise reduction algorithms. The files resulting from the operations of this module are: - video files.
- Registration of catalog, which allows to register a catalog of animal behavior. This module also allows you to relate to each category a button on the keyboard to facilitate categorical analysis. The resulting files of this module are called: behavioral catalog
- Shuffle, which allows you to shuffle video files so that both the experimenter and the person who performed the shuffle do not know the content of the video. The video registrations that went through this module we call blind videos.

# kinematic, morphological and categorical transcription tools

The kinematic, morphological and categorical transcription tools (etography) allow:
- Carry out the behavioral categorical transcription (TCC) of the videos. This is the process of categorizing the video frames into one of the categories of the behavioral catalog developed a priori. In the literature that the program acts this process is called etography. To facilitate TCC the program has a number of controllers related to the video advance (e.g., modification of playback speed, changes of frames at constant intervals). In order to adapt the result of the transcription to the user of the program, we call it: etography.
- Perform kinematic and morphological behavioral transcription (TCCM) of the video recorded. In the literature this process is called "Tracking", in Portuguese tracking. However, the program accomplishes more than just determining to each frame the position of the largest object on the scene. It also extracts morphological characteristics: area of ​​the animal, angle of the animal in relation to the frame, size of the animal and width of the animal. As kinematic characteristics: variation of animal's area, variation of angle, variation of size and variation of width. Kinematic and morphological transcription is performed using parallel processing algorithms. The results are also shown graphically at the time of behavioral transcription. For suitability with the literature the result of image processing we refer to for tracking.

# Kinematic and Morphological Transcription Analysis

The tools of Kinematic and Morphological Transcription Analysis and of etography allow to perform analyzes that are important for the field of study that the program operates, but are rarely found. You can do this by:
- Time segmentation of the tracking and spelling report. This module divides the TCC report and the TCCM report by a fixed period of time. For the CBT report, the result of segmentation is given in frequency, latency and duration of each behavior for each time interval. For the TCCM report, the report segments frames that are within the time range.
- Segmentation of the CBT and CBTM report by behavior. The behavioral targeting can partition the TCC and TCCM report from a catalog category. At the end of segmentation this algorithm generates a video with the frames found in the analysis and a report
- Segmentation of the TCCM report by area. The area-segmentation algorithm separates the TCCM result into different areas of interest previously recorded in the preparation tools.

- Agreement analysis between interobserver and intraobserver. The program calculates agreement between two auto-exclusive CBTs using the Cohen-Kappa method and between two self-exclusive CBTs using the Fleiss-Kappa method.
Sequential analysis that allows to count the succession of behaviors

# How to run

You will need to install [K-Lite Mega Codec Pack](https://k-lite-mega-codec-pack.br.uptodown.com/windows/download) to correct open your videos.


<!-- # Examples
 -->



<!-- # How to contribute. -->
