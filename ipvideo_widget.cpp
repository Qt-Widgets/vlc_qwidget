/*
 * Copyright (c) 2015, Alireza Hosseini.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Author: Alireza Hosseini */

#include "../include/blackvenus_tele/ipvideo_widget.hpp"
#include <ros/ros.h>

IpVideoWidget::IpVideoWidget(QWidget *input_parent, QString input_stream_url)
    :parent_widget_(input_parent),
     stream_url_(input_stream_url)
{
    ROS_INFO("IpVideoWidget Initializing...");

    vlc_instance_    = NULL;
    vlc_media_       = NULL;
    vlc_media_player_ = NULL;

    QPalette palette;
    palette.setColor(QPalette::Background,QColor::fromRgb(182,166,241));
    setPalette(palette);

    setAutoFillBackground(true);
}

bool IpVideoWidget::initializeCamera()
{
    return refresh();

}

bool IpVideoWidget::refresh()
{

    //release all vlc resources
    releaseCamera();

    /*Standard Format:
      rtsp://userName:password@hostAddress:port*/

    /*url = "http://192.168.10.46:80/cgi-bin/quad?USER=Admin&PWD=123456&DISPLAY=0";*/

    //ipcamera
    /*url = QString( "http://"
                       +cameraIp.toString()+"/image1?323145" );*/

    vlc_instance_ = libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]), vlc_args);
    libvlc_set_log_verbosity(vlc_instance_,-1);

    vlc_media_ =  libvlc_media_new_location(vlc_instance_ , stream_url_.toAscii() );

    libvlc_media_add_option          ( vlc_media_ , ":rtsp-caching=10" ); //decreasing delay
    libvlc_media_add_option          ( vlc_media_ , ":network-caching=10" );
    libvlc_media_add_option          ( vlc_media_ , ":ffmpeg-threads=1" );

    ROS_INFO_STREAM("IpVideoWidget::refreshing screen");

    vlc_media_player_ = libvlc_media_player_new(vlc_instance_);
    libvlc_media_player_set_media    ( vlc_media_player_ , vlc_media_ );
    libvlc_media_player_set_agl      ( vlc_media_player_ , parent_widget_->winId() );
    libvlc_media_player_set_xwindow  ( vlc_media_player_ , parent_widget_->winId() );
    libvlc_media_player_play         (vlc_media_player_);

    ROS_INFO_STREAM("IpVideoWidget:: aspect ratio of video had been set to 6:4");
    /*!TODO set aspect ratio value dynamically*/
    //libvlc_video_set_aspect_ratio   (vlcMediaPlayer,"6:4"); //in order to strech the video to fit in the widget
    return 1;
}

void IpVideoWidget::updateURL(QString new_url)
{
    stream_url_ = new_url;
}

void IpVideoWidget::releaseCamera()
{
    if(vlc_media_player_)
    {
        libvlc_media_player_release(vlc_media_player_);
    }
    if(vlc_media_)
    {
        libvlc_media_release(vlc_media_);
    }
    if(vlc_instance_)
    {
        libvlc_release(vlc_instance_);
    }
}
