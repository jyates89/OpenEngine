package com.avernakis.common;

import picocli.CommandLine;
import picocli.CommandLine.IVersionProvider;

import java.net.URL;
import java.util.Enumeration;
import java.util.jar.Attributes;
import java.util.jar.Manifest;

public class VersionInfo implements IVersionProvider {

  public String[] getVersion() throws Exception {
    Enumeration<URL> resources = CommandLine.class.getClassLoader().getResources(
        "META-INF/MANIFEST.MF");
    while (resources.hasMoreElements()) {
      URL url = resources.nextElement();
      Manifest manifest = new Manifest(url.openStream());
      Attributes attributes = manifest.getMainAttributes();
      String title = attributes.getValue("Implementation-Title");
      String buildDate = attributes.getValue("Build-Date");
      String buildVersion = attributes.getValue("Implementation-Version");

      if (title != null && buildVersion != null && buildDate != null) {
        return new String[]{
            title + " " + buildVersion + " " + buildDate,
        };
      }
    }
    return new String[]{
        "Build information not provided in manifest."
    };
  }
}
