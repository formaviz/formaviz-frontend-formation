# Formaviz-Front-Formation

## 1.Requirements

- NodeJS >9.x

## 2. Installation

First, clone this repository using
`git clone https://github.com/formaviz/formaviz-frontend-formation.git`

After that, open your favorite text editor and open the project. At this point, you must install project's depencies using `npm install`

If this part is correctly execute you can run `npm run build` to build project.

If your build was correctly finished, you can see something like this

```bash
[19/19] Building src\app-FrontFormaviz.cmj
✨  Built in 25.10s.

dist/app.b4006018.map      1011.64 KB     194ms
dist/app.c9ad6a22.js        303.34 KB    24.18s
dist/logo.67d49134.png       16.67 KB     4.98s
dist/index.html                 532 B      53ms
dist/app.35598450.css           246 B     1.27s
dist/style.4afcb011.map          97 B      16ms
dist/style.4afcb011.css          71 B    10.40s
```

## 3. Launch project

- In develop mode

In this project we use parcel to create project bundle. To run this project in dev mode, you can simple used this command.

`npm run parcel`

```bash
> parcel index.html

Server running at http://localhost:1234
✨  Built in 12.84s.

```

Then open your browser at http://localhost:1234 and simply enjoy

- In production mode

Simply run `npm start`

you can now see an output like this one

```bash
Formation server started on port 8080
```

Then open your browser at http://localhost:8080 and simply enjoy

Team Formaviz-Front
