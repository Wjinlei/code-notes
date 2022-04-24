FROM openjdk:11.0.13-jdk-buster

RUN mkdir /app

WORKDIR /app

COPY target/springboot-blog-1.0.0.jar /app

EXPOSE 8080

CMD ["java", "-jar", "springboot-blog-1.0.0.jar"]