// bleu clair : #467d97
// bleu foncé : #174666
// dorée : #f6c135
// gris : cecece

let navBarCss =
  ReactDOMRe.Style.make(
    ~backgroundColor="#467d97",
    ~color="white",
    ~display="flex",
    ~marginBottom="2%",
    ~flexDirection="row",
    ~justifyContent="end",
    (),
  );

let btnCSS = ReactDOMRe.Style.make(~color="white", ());

let logoContainerCSS = ReactDOMRe.Style.make(~height="90px", ());

let logoCSS = ReactDOMRe.Style.make(~height="90px", ~paddingRight="10px", ());

let btnNav = ReactDOMRe.Style.make(~color="white", ());

let btnNavHover = ReactDOMRe.Style.make(~color="#f6c135", ());